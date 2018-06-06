

with open("./Thread_12389", "r") as ins:
    array = []
    for line in ins:
    	if "EIP" in line:
    		line = line.split('EIP = ')[1]
        	array.append(int(line,16))
for l in array:
	print(l)  


