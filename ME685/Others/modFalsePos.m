format long;
a = input('Enter a value for lower boundary a: ');
b = input('Enter a value for upper boundary b: ');
n = input('How small should should the error be (to what -power)? ');

F = f(a);
G = f(b);
w0 = a;

iter=0;
while (1)
    iter = iter+1;
    wn = (G*a-F*b)/(G-F);
    disp([a b wn w0]) %%just checking where the values are, and it they look correct
    if f(a)*f(wn) > 0

       disp('ranif 1')%%just checking where the values are, and it they look correct
        b = wn;
        G = f(wn);
            if f(w0)*f(wn) > 0 
                F = F/ 2; end;
            disp('ranif 2')%%just checking where the values are, and it they look correct
            disp([a b wn w0])%%just checking where the values are, and it they look correct
    else 
        a = wn;
        F = f(wn);
            if f(w0)*f(wn) > 0 
               disp('ranif 3')%%just checking where the values are, and it they look correct
               disp([a b wn w0])%%just checking where the values are, and it they look correct
                G = G/ 2; end;
    end
    disp([a b wn w0])
    if (abs((wn - w0)/wn) < 0.5*10^-n)
        disp ('The root is: ')
        disp (wn)
        break; 
    else
        w0 = wn;
    end
    if iter==3
        break;
    end
end

function ans = f(x)
    ans = x^10-1;
end