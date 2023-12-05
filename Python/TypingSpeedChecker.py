import tkinter as tk

import random

import time


class TypingSpeedTestApp:

    def __init__(self, root):

        self.root = root

        self.root.title("Typing Speed Test")


        # Sample sentences for typing test

        self.sentences = [

            "The quick brown fox jumps over the lazy dog.",

            "Programming is fun and challenging.",

            "Python is a versatile programming language.",

            "Practice makes perfect.",

            "Coding is an essential skill in today's world."

        ]


        # Variables

        self.current_sentence = ""

        self.start_time = 0


        # UI Elements

        self.label_sentence = tk.Label(root, text="", font=("Helvetica", 14))

        self.label_sentence.pack(pady=20)


        self.entry_typing = tk.Entry(root, font=("Helvetica", 12))

        self.entry_typing.pack(pady=10)


        self.btn_start = tk.Button(root, text="Start Typing Test", command=self.start_typing_test)

        self.btn_start.pack(pady=10)


    def start_typing_test(self):

        # Choose a random sentence for typing test

        self.current_sentence = random.choice(self.sentences)


        # Display the sentence

        self.label_sentence.config(text=self.current_sentence)


        # Enable the entry widget for typing

        self.entry_typing.config(state=tk.NORMAL)

        self.entry_typing.delete(0, tk.END)


        # Enable the "Check Typing Speed" button

        self.btn_start.config(state=tk.DISABLED)


        # Record the start time

        self.start_time = time.time()


        # Bind the Enter key to the check_typing_speed method

        self.root.bind('<Return>', self.check_typing_speed)


    def check_typing_speed(self, event=None):

        # Calculate typing speed

        end_time = time.time()

        elapsed_time = end_time - self.start_time


        typed_text = self.entry_typing.get()

        typed_words = len(typed_text.split())


        words_per_minute = int(typed_words / (elapsed_time / 60))


        # Display the typing speed

        result_message = f"Your typing speed: {words_per_minute} words per minute"

        self.label_sentence.config(text=result_message)


        # Disable the entry widget and re-enable the "Start Typing Test" button

        self.entry_typing.config(state=tk.DISABLED)

        self.btn_start.config(state=tk.NORMAL)


        # Unbind the Enter key

        self.root.unbind('<Return>')


if __name__ == "__main__":

    root = tk.Tk()

    app = TypingSpeedTestApp(root)

    root.mainloop()