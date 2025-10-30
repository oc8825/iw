import sys
import argparse
from strands import Agent
from strands.models.openai import OpenAIModel

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
    "C code an names the file it can be found in"
)
parser.add_argument("prompt",
    type=str,
    help="name of the file containing code prompt"
)
parser.add_argument("testing",
    type=str,
    help="name of the file containing programname and test cases"
)

def main():
    try:
        args = parser.parse_args()
        
        # connect to LLMs
        qwen_agent = Agent(model=qwen_model, callback_handler=None)
        claude_agent = Agent(model=claude_model, callback_handler=None)
    
    except Exception as ex:
        parser.print_usage()
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)
    

if __name__ == "__main__":
    main()
