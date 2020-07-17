function sum=calculate(m)
if m==0
    sum=0;
else
    sum=calculate(m-1)+m;
end
d