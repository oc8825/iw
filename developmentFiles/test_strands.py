from strands import Agent
from strands.models.openai import OpenAIModel

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

qwen_agent = Agent(model=qwen_model, callback_handler=None)
print("qwen says:", qwen_agent("What is 2 + 3?"))

claude_agent = Agent(model=claude_model, callback_handler=None)
print("claude says:", claude_agent("What is 3 + 3?"))

# to run, first activate: .venv\Scripts\activate
