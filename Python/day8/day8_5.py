#ceaser cypher

charArray = list("abcdefghijklmnopqrstuvwxyz")

def encrypt(text, s):
    result = ""
    for i in range(len(text)):
        char = text[i]
        if (char.isupper()):
            result += chr((ord(char) + s - 65) % 26 + 65)
        else:
            result += chr((ord(char) + s - 97) % 26 + 97)
    return result

def decrypt(text, s):
    result = ""
    for i in range(len(text)):
        char = text[i]
        if (char.isupper()):
            result += chr((ord(char) - s - 65) % 26 + 65)
        else:
            result += chr((ord(char) - s - 97) % 26 + 97)
    return result


text = input("Enter a string: ")
s = int(input("Enter a number: "))
encrypted = encrypt(text, s)
print("Encrypted: " + encrypted)

decrypted = decrypt(encrypted, s)
print("Decrypted: " + decrypted)