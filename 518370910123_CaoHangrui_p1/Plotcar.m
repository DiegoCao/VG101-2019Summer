function car=Plotcar(car,carin)

for i=1:carin
    if car(i).out == 1
        continue;
    elseif car(i).cross==0
        continue;
    else
    car(i).carplot=Acardraw(car(i).x,car(i).y,car(i).type);
    end
    
end