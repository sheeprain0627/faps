
function[]=FaceWarp()

%read the base coordiantes
[x y] = textread('Ageprogression\base.txt', '%d %d', 22 );
base_points = vec2mat([x y],2);


%read targer img coordiants

for i=1:4
    
[x y] = textread(['db\80\' num2str(i) '.txt'], '%d %d', 22 );
input_points = vec2mat([x y],2);

I = imread(['db\80\' num2str(i) '.jpg']);
udata = [1 240];
vdata = [1 320];

t_concord   = cp2tform(input_points,base_points,'lwm',22); 
loc_affine_image = imtransform(I,t_concord,'XData',[1 udata(2)], 'YData',[1 vdata(2)]);

%imshow(I), 
%figure, imshow(loc_affine_image)
imwrite(loc_affine_image, ['Ageprogression\80\' num2str(i) '.jpg']);
end

end
