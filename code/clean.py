with open("range","r") as f:
    ran=f.read().split(",")

ran = [int(i) for i in ran]
if input("Are you sure you want to delete all cpp and compiled files? (Y/N)") == "Y":
    import os
    for N in ran:
        os.system(f"rm {N}.out {N}.cpp")

