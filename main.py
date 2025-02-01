from operations import ai, STT,TTS

def main():
    inp = input("enter speech")
    response = ai.ask_claude_to_decide(inp)
    TTS.text_to_speech(text=response)


if __name__ == "__main__":
    main()