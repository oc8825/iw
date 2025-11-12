import sys
import argparse
from strands import Agent
from strands.models.openai import OpenAIModel
import subprocess
import re
import os

# set up connection to Qwen LLM
qwen_model = OpenAIModel(
  client_args={
    "api_key": "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",
    "base_url": "https://openrouter.ai/api/v1"
  },
  model_id="qwen/qwen-2.5-72b-instruct",
  params={
    "temperature": 0.5,
    "max_tokens": 5000,
  }
)

# set up connection to Claude LLM
claude_model = OpenAIModel(
  client_args={
    "api_key": "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",
    "base_url": "https://openrouter.ai/api/v1"
  },
  model_id="anthropic/claude-sonnet-4",
  params={
    "temperature": 0.5,
    "max_tokens": 5000,
  }
)

# set up argparse
parser = argparse.ArgumentParser(
    description="Take in a file that contains a prompt describing " \
    "the code to be generated, and a file with the desired name of " \
    "this program and command line arguments to test the program " \
    "against. Through iteration with multiple LLMs, produces the " \
    "C code and names the file it can be found in"
)
parser.add_argument("name",
    type=str,
    help="name of this test case - will look for namePrompt.txt and " \
    "nameTesting.txt"
)

def extract_code(response):
  response = response.strip()

  # get rid of markdown fences by looking between ```
  if "```" in response:
    matches = re.findall(r"```(?:[a-zA-Z0-9]*)\n([\s\S]*?)```", response)
    if matches:
      response = max(matches, key=len).strip()
    
  # remove any explanations before the code
  for anchor in ["#include", "int main("]:
    if anchor in response:
      start = response.find(anchor)
      response = response[start:]
      break
  
  return response.strip()

def main():
    try:
        args = parser.parse_args()
        
        # connect to LLMs
        qwen_agent = Agent(model=qwen_model, callback_handler=None)
        claude_agent = Agent(model=claude_model, callback_handler=None)

        # read in prompt and file name
        prompt_name = "prompts/" + args.name + "Prompt.txt"
        testing_name = "testing/" + args.name + "Testing.txt"
        to_execute = args.name + "Testing.txt"

        with open(prompt_name, 'r', encoding="utf-8") as prompt_input:
          original_prompt = prompt_input.read()
        with open(testing_name, 'r', encoding="utf-8") as testing_input:
          filename = testing_input.readline().strip()
        filename_with_folder = "solutions/" + filename
        
        prompt_string = original_prompt
        num_comparisons = 0
        num_builds = 0

        have_match = False
        while not have_match and num_comparisons < 20:
          num_comparisons += 1

          # get Qwen's results
          qwen_response = str(qwen_agent(prompt_string))
          qwen_response = extract_code(qwen_response)
          with open(filename_with_folder, 'w', encoding="utf-8") as output:
            output.write(qwen_response)

          # try to run the code and continue reprompting until runs
          # properly, or max of 10 times
          successful_compile = False
          max_attempts = 10
          attempts = 0
          while not successful_compile and attempts < max_attempts:
            attempts += 1
            num_builds += 1
            executor_result = subprocess.run(
              ["python", "executor.py", to_execute, "Qwen"],
              capture_output=True,
              text=True
            )
            if executor_result.returncode == 3:
              print("failed compile, reprompting Qwen")
              reprompt = "I gave you this prompt:\n"
              reprompt += prompt_string + "\n\n"
              reprompt += "And you produced this code:\n"
              reprompt += qwen_response + "\n"
              reprompt += "But it doesn't compile. The compiler gave " \
                          "these errors:\n"
              reprompt += executor_result.stderr + "\n"
              reprompt += "Please fix the code so it compiles successfully " \
                          "and follows the same prompt given above. Return " \
                          "only valid C code - no explanations or markdown " \
                          "fences. Start your response directly with code."
              qwen_response = str(qwen_agent(reprompt))
              qwen_response = extract_code(qwen_response)
              with open(filename_with_folder, 'w', encoding="utf-8") as output:
                output.write(qwen_response)
            elif executor_result.returncode == 0:
              print("successful compile")
              successful_compile = True
            else:
              print("Executor failed with some other error")
              sys.exit(1)

          if not successful_compile:
            print("Failed to compile successfully after 10 attempts")
            sys.exit(1)

          # get Claude's results
          claude_response = str(claude_agent(prompt_string))
          claude_response = extract_code(claude_response)
          with open(filename_with_folder, 'w', encoding="utf-8") as output:
            output.write(claude_response)

          # try to run the code and continue reprompting until runs
          # properly, or max of 10 times
          successful_compile = False
          max_attempts = 10
          attempts = 0
          while not successful_compile and attempts < max_attempts:
            attempts += 1
            num_builds += 1
            executor_result = subprocess.run(
              ["python", "executor.py", to_execute, "Claude"],
              capture_output=True,
              text=True
            )
            if executor_result.returncode == 3:
              print("failed compile, reprompting Claude")
              reprompt = "I gave you this prompt:\n"
              reprompt += prompt_string + "\n\n"
              reprompt += "And you produced this code:\n"
              reprompt += claude_response + "\n"
              reprompt += "But it doesn't compile. The compiler gave " \
                          "these errors:\n"
              reprompt += executor_result.stderr + "\n"
              reprompt += "Please fix the code so it compiles successfully " \
                          "and follows the same prompt given above. Return " \
                          "only valid C code - no explanations or markdown " \
                          "fences. Start your response directly with code."
              claude_response = str(claude_agent(reprompt))
              claude_response = extract_code(claude_response)
              with open(filename_with_folder, 'w', encoding="utf-8") as output:
                output.write(claude_response)
            elif executor_result.returncode == 0:
              print("successful compile")
              successful_compile = True
            else:
              print("Executor failed with some other error")
              sys.exit(1)

          if not successful_compile:
            print("Failed to compile successfully after 10 attempts")
            sys.exit(1)

          qwen_out = "results/" + filename.split('.')[0] + "Qwen.out"
          claude_out = "results/" + filename.split('.')[0] + "Claude.out"
          comparator_result = subprocess.run(
            ["python", "comparator.py", qwen_out, claude_out],
            capture_output=True,
            text=True
          )
          if comparator_result.returncode != 0:
            print("Comparator failed:", comparator_result.stderr)
            sys.exit(1)

          with open("Comparator.out", 'r', encoding="utf-8") as comparator_input:
            status = comparator_input.readline().strip()
            if status == "Matching Output":
              print("Claude and Qwen agree on the solution found in", filename_with_folder)
              print("Total number of program builds:", num_builds)
              print("Total number of comparison iterations:", num_comparisons)
              have_match = True
            else:
              differing_feedback = comparator_input.read()
              print("Results didn't match, reprompting both with feedback")
              prompt_string = "I originally gave you, and one other LLM, the prompt outlined below: \n"  + original_prompt + \
              "One given solution was: \n" + qwen_response + \
              "The other provided solution was: \n" + claude_response + \
              "However, after running these two solutions, the output differed in these sections: \n" + differing_feedback + \
              "Given this information of the two solutions and where they differ, please write a new solution " \
              "that conforms to the original prompt repeated above. Return only valid C code - no explanations or markdown " \
              "fences. Start your response directly with code."
        
        if not have_match:
          print("Failed to find agreement after 20 iterations")
    
    except Exception as ex:
        parser.print_usage()
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)
    

if __name__ == "__main__":
    main()
