# this is going to make the choices using a LLM

import anthropic
import os

ANTHROPIC_API_KEY = os.getenv("claude_key")

client = anthropic.Anthropic(api_key=ANTHROPIC_API_KEY)

#Options that are viable for the AI 
options = [
        "Option A: Give a good comeback",
        "Option B: change the enviornment",
        "Option C: get emergeny services online"
    ]
def ask_claude_to_decide(options, criteria):
    """
    Ask Claude to decide between options based on given criteria.
    
    :param options: List of options to choose from.
    :param criteria: Criteria to evaluate the options.
    :return: Claude's decision and reasoning.
    """
    # Construct the prompt
    prompt = f"""You are an intelligent Robot that can move around ones home and Answer questions and help with automation tasks:
    
    Options:
    {', '.join(options)}

    Criteria for decision-making:
    {criteria}

    Please analyze the options based on the criteria and provide:
    1. Your recommended choice.
    2. A reasonable comment based on what the user says.
    3. If changing the enviornment say how to change the enviornment

    Answer the response in the form: 1 "%", 2 "%", 3"%"
    """

    # Send the prompt to Claude
    response = client.messages.create(
        model="claude-3-opus-20240229",  
        max_tokens=500, 
        messages=[
            {"role": "user", "content": prompt}
        ]
    )

    #return Claude's response
    return response.content[0].text



