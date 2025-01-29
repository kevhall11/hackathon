import speech_recognition as sr
recognizer = sr.Recognizer()
#run for imput to gpt 
def mic():
    """Function to listen to the microphone and recognize speech."""
    with sr.Microphone() as source:

        # Adjust for ambient noise and record the audio
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)

        try:
            # Use Google Web Speech API to recognize the audio
            text = recognizer.recognize_google(audio)

        except sr.UnknownValueError:
            text = None 
        except sr.RequestError as e:
            text = None


    return text  # Continue listening
    

while True:
    mic()

