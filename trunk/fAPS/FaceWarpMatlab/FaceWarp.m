
function[]=FaceWarp()
%read the base coordiantes
[x y] = textread('Ageprogression\base.txt', '%d %d', 23 );
base_points = vec2mat([x y],2);

%read the folders and images
[folder images] = textread('db\folder.txt', '%d %d', 6 );

In = imread('Ageprogression\2_output.bmp');
siz=size(In);
%read targer img coordiants

for fo=1:6

for i=1:images(fo)
    
[x y] = textread(['db\' num2str(folder(fo)) '\' num2str(i) '.txt'], '%d %d', 23 );
input_points = vec2mat([x y],2);

I = imread(['db\' num2str(folder(fo)) '\' num2str(i) '.jpg']);
udata = [1 siz(2)];
vdata = [1 siz(1)];

t_concord   = cp2tform(input_points,base_points,'lwm',22); 
loc_affine_image = imtransform(I,t_concord,'XData',[1 udata(2)], 'YData',[1 vdata(2)]);

%imshow(I), 
%figure, imshow(loc_affine_image)
imwrite(loc_affine_image, ['Ageprogression\' num2str(folder(fo)) '\' num2str(i) '.jpg']);
end
end
end
