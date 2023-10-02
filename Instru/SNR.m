img =imread(".png");    %Reading the image
%img = sis_output.image
bw=rgb2gray(img);            %Converting to grayscale
%bw=img
n=input('sub_array length:');                        %defining width of image subarray having brightest star
bw1 = bw;               % A copy of image for tagging bright pixels   
l=input('Length:');
b=input('Breadth:');
threshold= input('Threshold grayscale value:');
for i = 1:l             % Tagging the image
    for j = 1:b
        if(bw(i,j)>threshold)
           bw1(i,j)=1;
        else
           bw1(i,j)=0;
        end       
    end 
end
max_pixel = max(bw(:)) ; %Maximum grayscale value

v= nonzeros(bw1); % No of bright pixels
[i,j,v] = find(bw1);    %Location of bright pixels    
Pixels = cat(2,i,j);    
for i = 1:l   
    for j = 1:b
        if(bw(i,j)==max(bw(:)))
            rand_pixel =[j,i];  
            break
        end
    end 
end
n1=0;
n2=0;
n3=0;
n4=0;
for i=1:240
        if(bw1(rand_pixel(1,2)-i,rand_pixel(1,1))==1)
            n1=n1+1;
        else 
            break
        end
end
for i=1:240
        if(bw1(rand_pixel(1,2)+i,rand_pixel(1,1))==1)
            n2=n2+1;
        else 
            break
        end
end
for i=1:240
      if(bw1(rand_pixel(1,2),rand_pixel(1,1)-i)==1)
            n3=n3+1;
      else 
            break
      end
end
for i=1:240
      if(bw1(rand_pixel(1,2),rand_pixel(1,1)+i)==1)
            n4=n4+1;
      else 
            break
      end
end
nx =max(n1,n2);
ny=max(n3,n4);
p=max(nx,ny);
if(rem(p,2)==1)
    p=p-1;
end

        
imtool(bw);
submatrix = bw(rand_pixel(1,2)-(n/2-1):rand_pixel(1,2)+n/2,rand_pixel(1,1)-(n/2-1):rand_pixel(1,1)+n/2);
submatrix = double(submatrix);
ima=mean(bw(:));
submatrix_1 = submatrix - ima;
star_pixels = submatrix_1(n/2-p/2:n/2+p/2,n/2-p/2:n/2+p/2);
sig=mean(star_pixels(:));
std_array= zeros(n^2-n,1);
m=1;
for i = 1:n
    if(i<n/2-2 || i>n/2+2)
        for j = 1:n
            if(j<n/2-2 || j>n/2+2)
                std_array(m)= submatrix_1(i,j);
                m=m+1;
            end
        end
    end
end
noise=std(std_array(:));
snr= sig/noise;
