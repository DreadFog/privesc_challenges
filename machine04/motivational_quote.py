import random
# read a random line from the file /root/poem.txt
def get_random_line(file_name):
    lines = open(file_name).read().splitlines()
    return random.choice(lines)
# print a random line from the file /root/poem.txt
print(get_random_line("/root/poem.txt"))