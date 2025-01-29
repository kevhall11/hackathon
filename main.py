from operations import ai, TTS

def main():
    input = TTS.mic()
    response = ai.ask_claude_to_decide(input)
    print (response)


if __name__ == "__main__":
    main()