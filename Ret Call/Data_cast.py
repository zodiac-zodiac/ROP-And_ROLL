
i = 0 
with open("./test1_vuln_example.txt", "r") as ins:
    array = []
    for line in ins:
    		i = i +1
    		line = line.split("RET count : ")[1]
    		ret = line.split(" CALL count : ")[0]
    		call = line.split(" CALL count : ")[1].split(" Current")[0]
    		line = str(i) +','+ret +','+ call
        	array.append(line)
for l in array:
	print(l)  


