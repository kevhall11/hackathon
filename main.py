from operations import ai, STT,TTS

def main():
    input = STT.mic()
    response = ai.ask_claude_to_decide(input)

    
    TTS.text_to_speech(text=response)


if __name__ == "__main__":
    main()