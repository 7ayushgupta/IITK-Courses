% The maximum value of error after which we need to stop the program
MAX_ERROR = 1e-9;

% Inital guesses for x1 and x2 as the interval boundaries
x1 = 0;
x2 = pi/2;

y1 = f(x1);
y2 = f(x2);

% Main iterations for algorithm
if y1*y2<0
   error = min(abs(y1), abs(y2));

   while error > MAX_ERROR
       x0 = (x1+x2)/2;
       y1 = f(x1);
       y0 = f(x0);
       error = min(abs(y1), abs(y2));
       fprintf("x1: %f, x2: %f, x0: %f, f(x0): %f, f(x1): %f. f(x2): %f\n", x1, x2, x0, f(x0), f(x1), f(x2));

       if error < MAX_ERROR
           if abs(y1)<MAX_ERROR
               x0 = x1;
           end
       elseif y1*y0 > 0
           x1 = x0;
       else
           x2 = x0;
       end
   end
else
    fprintf("Invalid output %f %f", y1, y2);
end

fprintf("Root of the function is: %f\n", x0);
    
function ans = f(x)
    ans = x*tan(x)-1;
end