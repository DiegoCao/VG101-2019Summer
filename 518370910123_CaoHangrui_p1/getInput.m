function [g,o,r,p,n,w,letter,Left_pro]= getInput()
g=input('the time for green light (0.1s)(recommend:180-200)\n');
while(g<=0)
    disp('wrong input. The time for lights should be larger than 0');
    g=input('the time for green light\n');
end
o=input('the time for orange light(suggested 40-60) \n');
while(o<=0)
    disp('wrong input. The time for lights should be larger than 0 (suggested 40-60)');
    o=input('the time for orange light\n');
end
disp('Notice: if the r = o+g, it is the same to the case in real life. But the input is your choice.');
r=input('the time for red light(suggested 200-260)\n');

while(r<=0)
    disp('wrong input. The time for lights should be larger than 0 (suggested 140-160)');
    r=input('the time for red light\n');
end
p=input('the probability for running the red light(between0.00-1.00)\n');
while(p<0||p>1)
    disp('wrong input. The probability for running lights should be larger than 0, smaller to 1');
    p=input('the probability for running the red light(between0.00-1.00)\n');
end
n=input('the number of the cars\n');
while(n<=0||mod(n,1)~=0)
    disp('wrong input. The number of the car should be an interger larger than 0');
    n=input('the number of the cars\n');
end
w=input('the width of the road (suggested: 20-40)\n');
while(w<0)
    
    disp('wrong input.The width of should be larger than 0');
    w=input('the width of the road \n');
end
letter=input('please input more than seven characters\n','s');
while(length(letter)<7)
    letter=input('more than seven characters, thanks!\n','s');
end
Left_pro=input('input the possibility to turn left : suggested(0.4-0.5)\n, ');

end