import os
os.system("module load gcc")
with open("range","r") as f:
    ran=f.read().split(",")

ran = [int(i) for i in ran]

with open("main.cpp","r") as f:
    text=f.read()

for l in [10,15,20,30]:
    for N in ran:
        print(f"N={N} len={l}")
        # print(f"id={int(os.getenv('SLURM_ARRAY_TASK_ID'))} N={ran[int(os.getenv('SLURM_ARRAY_TASK_ID'))]}")
        # N=ran[int(os.getenv('SLURM_ARRAY_TASK_ID'))]
        text2=text.replace("number_of_objects",str(N)+";")
        with open(f"{N}_{l}.cpp","w") as f:
            f.write(text2)
        os.system(f"g++ {N}_{l}.cpp -o {N}_{l}.out")
        print(f"Compiled {N}_{l}.cpp")
        os.system(f"nohup ./{N}_{l}.out > res/{N}_{l}.csv &")
        print(f"Started {N}_{l}.out")