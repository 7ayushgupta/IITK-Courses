%Soumya Gupta PA-2 Question 1 170713
fprintf("Choose from The following and give input accordingly: \n");
fprintf("A. Solve a System of Equation \n");
fprintf("B. Perform a LU decomposition \n");
fprintf("C. Perform a Matrix Inversion \n");
str=input('what is your choice\n','s');
if str == 'A'
    fprintf("Choose method : /n Y. Thomas Algorithm /n N. Gauss Elimination\n");
    ch=input('what is your choice\n','s');
    %--------------------Gauss Elimination---------------
    if ch == 'N'
         fprintf("Input a file  \n Format: \n size \n matrix and vector augmented\n");
         file=fopen("input-gauss.txt");
         line=fgetl(file);
         n=sscanf(line, '%f' );
         A=zeros(n,n);
         temp=zeros(1,n);
         for i=1:1:n
           line = fgetl(file);
           A(i,1:1:n+1) = sscanf(line, '%f ');
         end;
         for i=1:1:n-1
             for j=i+1:1:n
                 large=A(i,i);
                 index=i;
                 if abs(large)<abs(A(j,i))
                     large=A(j,i);
                     index=j;
                 end
             end
             temp=A(i,:);
             A(i,:)=A(index,:);
             A(index,:)=temp;
             for j=i+1:1:n
               A(j,:) = A(j,:)-(A(j,i)/A(i,i))*A(i,:);
             end;
         end;
         X = zeros(n,1);
          X(n,1) = A(n,n+1)/A(n,n);
          for i=n-1:-1:1
            for j=n:-1:i+1
              X(i,1) = A(i,n+1)-X(j,1)*A(i,j);
            end;
            X(i,1) = X(i,1)/A(i,i);
          end;
          
          filename = 'output-gauss.txt';
          outf = fopen (filename, 'w');
          fprintf(outf,"Guass Elimination(with pivoting) \r\n X \r\n");
          fprintf(outf,'%6.4f\r\n',X);
          fclose(outf);
    end

    %------------------------thomas--------------------
    if ch == 'Y'
        fprintf("Input a file  \n FORMAT \n size \n l vector \n d vector \n u vector \n b vector\n");
        file=fopen("input-thomas.txt");
         line=fgetl(file);
         n=sscanf(line, '%f' );
         A=zeros(n,n);
         temp=zeros(1,n);
         line = fgetl(file);
         l(1:1:n) = sscanf(line, '%f ');
         line = fgetl(file);
         d(1:1:n) = sscanf(line, '%f ');
         line = fgetl(file);
         u(1:1:n) = sscanf(line, '%f ');
         line = fgetl(file);
         b(1:1:n) = sscanf(line, '%f ');

          for i=1:1:n
              if i==1
                  alpha(1)=d(1);
                  beta(1)=b(1);
              else
                  alpha(i)=d(i)-((l(i)/alpha(i-1))*u(i-1));
                  beta(i)=b(i)-((l(i)/alpha(i-1))*beta(i-1));
              end      
          end
          X(n)=beta(n)/alpha(n);
          for i=n-1:-1:1
              X(i)=(beta(i)-(u(i)*X(i+1)))/alpha(i);
          end
          filename = 'output-thomas.txt';
          outf = fopen (filename, 'w');
          fprintf(outf,"Thomas Algorithm \r\n X \r\n");
          fprintf(outf,'%6.4f\r\n',X);
          fclose(outf);
    end
end
if str == 'B'
    fprintf("Choose method : \n Y. Cholesky \n N. Doolittle or crout\n");
    ch=input('what is your choice\n','s');
    fprintf("Input a file  \n Format: \n size \n matrix and vector augmented\n");   
    file=fopen("input-LU.txt");
    line=fgetl(file);
    n=sscanf(line, '%f' );
    A=zeros(n,n);
    temp=zeros(1,n);
    for i=1:1:n
       line = fgetl(file);
       A(i,1:1:n+1) = sscanf(line, '%f ');
    end;
%-----------------------cholesky--------------------
    if ch == 'Y'
     
     for k = 1:n-1
         [maxc, rowindices] = max( abs(A(k:n, k:n)) );
         [maxm, colindex] = max(maxc);
         row(k) = rowindices(colindex)+k-1; col(k) = colindex+k-1;
         A( [k, row(k)], : ) = A( [row(k), k], : ); 
         A( :, [k, col(k)] ) = A( :, [col(k), k] );
         indices=[row;col];
         if A(k,k) == 0
           break
         end
     end
       L = zeros(n,n);
       L(1,1) =sqrt(A(1,1));
       L(2:n,1) = A(2:n,1)/L(1,1);
     
       for j=2:n
         s1=0;
         for l = 1:j-1;
           s1 = s1 + L(j,l)*L(j,l);
         end;
         L(j,j)=sqrt((A(j,j)- s1));
         for i=j+1:n
           s1=0;
           for l = 1:j-1;
             s1 = s1 + L(i,l)*L(j,l);
           end;
           L(i,j)=(A(i,j)- s1)/L(j,j);
         end
       end  
       filename = "output-LU-Cholesky.txt";
       outf = fopen(filename, "w");
       fprintf(outf,"exchanges are made at following index: \r\n");
       fprintf(outf,"   row  column \r\n");
       fprintf(outf,"%6.1f %6.1f \r\n",indices );
       fprintf(outf ,"Cholesky Method\n\r\nL:\r\n");
       for i=1:1:n
          fprintf(outf,'%6.4f  ',L(i,:));
          fprintf(outf,'\r\n');
       end
       fclose(outf);
    end
  
%------------------------doolittle & crout's 
    if ch == 'N'
       for k = 1:n-1
         [maxc, rowindices] = max( abs(A(k:n, k:n)) );
         [maxm, colindex] = max(maxc);
         row(k) = rowindices(colindex)+k-1; col(k) = colindex+k-1;
         A( [k, row(k)], : ) = A( [row(k), k], : ); 
         A( :, [k, col(k)] ) = A( :, [col(k), k] );
         indices=[row;col];
         if A(k,k) == 0
           break
         end
       end
     fprintf("Enter your choice \n 1.Doolittle \n 2.Crout\n");
     meth = input('');
         if meth==1
                 
                     L=zeros(n,n);
                     U=zeros(n,n);
                     U(1,:)=A(1,1:n);
                     L(:,1)=A(:,1)/U(1,1);
                     L(1,1)=1;
                     for k=2:n
                         for i=2:n
                             for j=i:n
                                 U(i,j)=A(i,j)-dot(L(i,1:i-1),U(1:i-1,j));
                             end
                             L(i,k)=(A(i,k)-dot(L(i,1:k-1),U(1:k-1,k)))/U(k,k);
                         end
                     end
                     filename = "output-LU-Doolittle.txt";
                outf = fopen(filename, "w");
                fprintf(outf,"exchanges are made at following index: \r\n");
                fprintf(outf,"   row  column \r\n");
                fprintf(outf,"%6.1f %6.1f \r\n",indices );
                fprintf(outf ,"Doolittle Method\r\n");
                fprintf(outf ,"L: \r\n");
                for i=1:1:n
                   fprintf(outf,'%6.4f  ',L(i,:));
                   fprintf(outf,'\r\n');
                end
                fprintf(outf ,"U: \n");
                 for i=1:1:n
                   fprintf(outf,'%6.4f  ',U(i,:));
                   fprintf(outf,'\r\n');
                end
                fclose(outf);
         end
         if meth==2
             L=zeros(n,n);
                     U=zeros(n,n);
                     L(:,1)=A(1:n,1);
                     U(1,:)=A(1,1:n)/L(1,1);
                     U(1,1)=1;
                     for k=2:n
                         for j=2:n
                             for i=j:n
                                 L(i,j)=A(i,j)-dot(L(i,1:j-1),U(1:j-1,j));
                             end
                             U(k,j)=(A(k,j)-dot(L(k,1:k-1),U(1:k-1,j)))/L(k,k);
                         end
                     end
                     filename = "output-LU-Crout's.txt";
                outf = fopen(filename, "w");
                fprintf(outf,"exchanges are made at following index: \r\n");
                fprintf(outf,"   row  column \r\n");
                fprintf(outf,"%6.1f %6.1f \r\n",indices );
                fprintf(outf ,"Crouts Method\r\n");
                fprintf(outf ,"L: \r\n");
                for i=1:1:n
                   fprintf(outf,'%6.4f  ',L(i,:));
                   fprintf(outf,'\r\n');
                end
                fprintf(outf ,"U: \r\n");
                 for i=1:1:n
                   fprintf(outf,'%6.4f  ',U(i,:));
                   fprintf(outf,'\r\n');
                end
                fclose(outf);
         end
    end
end