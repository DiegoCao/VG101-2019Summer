#README FILE FOR PROJECT ONE
##The basic instructions to use the programs
-----
###The catalog for README
1. Start using (How to run this program)
2. Specifications of my choice in this program
3. details of some important functions in this program
4. specifications for plate producing

------

##Start using
1. There are functions with .m in the folder. Run the function which is called 'Main' in that folder. 
2. if you notice that the animation is not very smooth, press Ctrl+C, and type in clf, clearvars in command line.
------
### Mode choose
1. The program allow the user to choose three difficulty level. 
   >The easy mode: the program automatically produces all the parameters needed.
   >The hard mode: the program only provides suggested range of input. (can have choice to some hints)
2. To quickly uses the program and see effects of most of the functions, easy mode is recommended(since it is convenient). To test more functions such as detecting crash, user can use hard mode.
3. If you want to see more car appear on the road and more willing to see the slowdown or crash, do choose the fast producing car rate.
------   
### Input format
1. These part is done by a getInput function.
2. In the medium and hard mode, the user would input following parameters:
   >g: the duration time for the green light (Suggested input range: )
   >r: the duration time for the red light   (Suggested input range:)
   >o: the duration time for the orange light (Suggested input range:)
   >p: probability to run red lights 
   >n: numbers of the car
   >w: width of the road   (Suggested input range: 20-30)
   >V_carproduce: the frequency of producing cars:(notice: if produce too often, it is more easier to crash)
   >Letters: a string containing at least more than five numbers or letters(to make plates for the car). 
   >Turnleft possibility:  Actually, this can be deleted
 
   >Produce car rate: the program automatically and randomly produces one car within certain amount of time.
 To give users more choices, user can choose the produce car rate slow, medium and fast.
3. Obviously, there are some basic rules for the parameters. For example, the g, r, o, n, w should be larger than zeros, 
the probability should lie between 0 and 1. If the user gives some wrong input, 
the function would prompt the user until he or she gives the right input.
4. The input value for the 'g, r, o' is not count in the unit of 's'. The unit of g, r, o is 0.1s.
5. Notice that users should input at least one letter, since first element of the plate is an letter. 
Also, it is suggested that users input more than 7 characters, since the permulations should exceed the number of the car.

## Spefications of my choice in this program
1. Notice that for the red lights, it is possible that four lights can be all red or green at the same time. It is up to the input of the user. The manual says that the lights on the triangle changes in the same way.
 It doesn't say four lights should change in the same way. Since this is like a game, the user need correct input of g, r, o to make the program function well.
2. There is very, very small possibility that the car would crash, since I set the car that can automatically wait for the car infront of it to cross. In my test cases, they 
3. The car who runs the red light would also run the orange light.


## Details of the program
The getinput function is explained in the previous part.
### How do the program regard 'one car'?

1. Every car has some information. Thus, we apply the data structure to one car. This makes the program more changeable, since if I want to add some applications, just add one element in one structure.
The struct for this car is listed as follows:
> car.type: the type of one car.
> car.direction: the direction here, refers to the 'lanes' of the road the car is in. The road is regarded as 16 lanes. When the car enters another lane(by crossing the crossroads), the car.direction would change.
For car information:
> car.plate: the plate of the car
> car.width: width of the car
> car.length: length of the car. The length and width are randomly produced and they can change.
For car speed:
> car.speed: the speed of the car. It can automatically change, by the functions that would be mentioned later.
> car.Vangle: the angular velocity of the car that turn left or right. It can also be automatically changed.
For postion:
>car. x:  a 1x4 array, storing the x value of four vertexes of one car.
>car. y: a 1x4 array, storing the y value of four vertexes of one car.
>car.cpositon: a 1X2 array, storing the coordinates of the center postion of the car.
>car.angle: the angle that the car has already turned.  
It seems repetitive to store both x,y and cpostion, yet for different functions, we use x,y or cpostion for simplicity.
others:
> car. runlight: only two value: 0 or 1. 1 indicates that the car would run the red light.
> car. cross: six values, 0, 1, 2, 3, 4, 5. It actually reflects the conditions of the car:
  0: not yet in
  1: in but not reach the cross
  2: waiting at the cross(for those do not run red lights)
  3: at cross
  4: passing the cross
  5: out of the road
2. Also, I set some variables: 
   Carin: numbers of cars that have been produced.
   Crosscar: numbers car that have crossed the road.
   Passcar: numbers car that have crossed the road. 

### How this program count time?
1. The program use while+pause to count the time passes.
Namely, when going through one loop, the time would add up.


##Details of some important functions
### carMove 
1. Notice: When this program is 'moving the cars', it first change the coordinates of the x, y and center position. 
2. According the the car.cross conditions, the function deals each of them accordingly. For example, if the car is at cross, according to its turning type, we move it straightly or use the 'rotateCar' function to rotate this car.
3. the 'rotateCar' function is used to rotate the car in a smooth way.
   

   
### detectCrash
1. As it is mentioned before, evert car contains the information of the coordinates of its four vertexes(x,y). Every car forms a rectangle. If one rectangle overlaps another, the car would crash.
2. The program uses 'inpolygon' function to determine whether one point is contained in another rectangle. It is very accurate. Even if the point is on the edge of another rectangle, it can detected.
3. Here we see the advantages of defining four points in a car structure. The inpolygon can be use as follows:
   IN1=inpolygon(car(i).x(1),car(i).y(1),car(x).x,car(j).y)
   we have mentioned before: the car.x is a 1x4 array, like [1,2,3,4]. Thus, the code above can test whether the x(1) of car(i) has touch the car(j). Proceed the x(2), x(3),x(4) 
likewise. If IN1+IN2+IN3+IN4 is larger than 0, it indicates that at least one point is containing in others.
4. We use two nest 'for' loops to determine whether any two cars have touched each other.
   Like for i=1:carin-1
            for j=i+1:carin
            ...
            end
        end
5. Notice: there is only very small possibility that the car would crash, since the car can automatically avoid car crash.

##Ploting part

### Drawroad 
use fill function to draw all roads;

### Plotcar & Acardraw
Acardraw: a subfunction that draws one car
Plotcar: deal with all the car on the roads. The car has different size and different lengths, randomly produced in a range. 

##Speed change part

### speedChange
1. in this part, the program aumatically counts the distance between the car itself and the car infront of it. According to the distance, the program would adjust the car(j).speed. 
2. Notice: When we are seeing the program, the car does not change the speed in a sudden. It changes its speed 'smoothly'. Namely, it has the effect of acceleration and 'brake stop distance';
3. I use the loop to ensure that every car can be detected. Namely, no rear-end would ever happen due to this system. 
   Specifically, distance=norm(car(i).cposition-car(j).cposition); 
   Then for different distance, compare it with car(j).length+car(i).length + Safetydistance(k)
   Safedistance is an array, containing different distance. When distance is small, the car would gradually slow down in a relatively smooth way.
4. Some specifications:
   If there is no other car in this road, the velocity of the car would increase and gradually reach the highest.s
   
   
###avoidcarCrash
1. In this part, I simulate the way in our daily life.
   In daily life, how do people know the crash might happen? they see the car infront of them is very near them, or they use the 'vehicle detector',(which is frequently seen in our cars). 
The vehicle detector can sense a certain distance infront of the car, and determine whether there exists barriers in that place.
2. Thus, when I write the avoidcarCrash function, I set the 'Detectlength' for each car, in case that it can detect the car infront of it. 
    Namely, use the geometric equation, we can calculate  the car(i).x'(3):
    For rotatescar: tempcar(i).x'(3)=tempcar(i).x(3)+(or -) Detectlength*cos(tempcar(i).angle)(or sin(tempcar(i).angle))
    For going straight car, the angle is 0 or pi/2;
    The x(4), y(3), y(4) can be calculated accordingly. Why we leave x(1) and x(2)? because in our program, the '3,4' points are the forepart of the car.
    Specifically, if [tempcar(i).x'(3),tempcar(i).y'(3)] or [tempcar(i).x'(4),tempcar(i).y'(4)]lies in another car, then the crash can be predicted.
 Notice: In this function, we would not change the actual car(i).x(3). The duplicated tempcar(i).x(3)is used to do a 'simulation'.
    If the simulation has detected the crash, it would stop corresponding car. For example, it would stop car(i), since there is another car infront of it.
3. Notice that through this method, all the cars that are lies in the road can be   

4. In very small cases, the crash would still happen if too many cars run the lights or you produce the car too fast.
5. This function accompany with the InitialCrosscar function. This is because after I stop the car(i), it cannot be stopped forever. So while entering the new loop, I reset the car(i).


--------
###Extra specifications for the 'plates'
1. I write two function of the plates production.
2. Alogorithm for exercise 1(it is in the dealAll.m function)
   The dealAll function solves the first problem with recursion.
   This problem actually asks us to select use recursive method to find the permulations. 
   Recursion for permulations
   It would go through the base case, until it reaches the last of the letter that is needed.
   For permulations, one simple algorithm goes as follows:
    Algorithm:
    rst=producePerm(array, size, N)

    if N == size
        rst=array;
    else     
        rst='';
        for i = N:size
            swap(array(i),array(N));
            rev=producePerm(array, size, N+1);
            rst=[rev,rst];
            swap(array(i),array(N));
        end
    end
    end
  

3. I use the randperm function in my plate design. Namely, once in a recursion, one plate would be produced. The plate would be compared with previous plates before. If the plate is used, it would replace the plate. This is shown in the makePlate.m file
