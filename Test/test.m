%% ------- This code is used for transfer of axes --------%%

%% ------- Read data from txt --------%%
clc
close all
clear all

D = importdata('PositionInfo.txt');

%% -------deal with data ------- %%
point_lontitude =108.57;% input('请输入中心点经度值：');
point_latitude = 34.16;%input('请输入中心点纬度值：');
angle = 30;%input('请输入视图纵轴与正北方向夹角（顺时针，-180°~180°）：');

figure(1);
plot(D.data(:,2), D.data(:,3), '.');
xlabel('经度/°');
ylabel('纬度/°');
grid on;
hold on;
plot(point_lontitude, point_latitude, 'r*');

figure(2);
plot3(D.data(:,2), D.data(:,3), D.data(:, 4), 'r.');
xlabel('经度/°');
ylabel('纬度/°');
zlabel('高程/m');
grid on;

%get center point
point_len = length(D.data);
point = D.data(:,2:4);
min = 10000;
point_cen = 1;
for i = 1:point_len
    temp = abs(point(i,1) - point_lontitude) + abs(point(i,2)-point_latitude);
    if temp < min
        min = temp;
        point_cen = i;
    end
end
min
point_cen

point_cen_lah = D.data(point_cen, 2:4);%center point position
points_all = zeros(point_len, 3);

for i = 1:point_len
    points_all(i,:) = get_pos(point(i, :), point_cen_lah);
end

figure(3)
plot(points_all(:, 1), points_all(:, 2), '*');
hold on
plot(points_all(point_cen, 1), points_all(point_cen, 2), 'ro');
xlabel('x/m（纬度线方向）');
ylabel('y/m（经度线方向）');
grid on
title('以与中心点的纬度线和经线为横纵轴的坐标系');

figure(4)
plot3(points_all(:, 1), points_all(:, 2), points_all(:, 3), 'r*');
grid on
xlabel('x/m（纬度线方向）');
ylabel('y/m（经度线方向）');
zlabel('相对中心点的高程/m');
title('以与中心点的纬度线和经线为横纵轴的坐标系');

points_trans = zeros(point_len, 3);%移动坐标轴到与正北方向设定角度
T = [cos(-angle * pi/180.0) sin(-angle * pi/180.0) 0;
    -sin(-angle * pi/180.0) cos(-angle * pi/180.0) 0;
    0 0 1];
points_trans = points_all * T';

figure(5)
plot(points_trans(:, 1), points_trans(:, 2), '*');
hold on
plot(points_trans(point_cen, 1), points_trans(point_cen, 2), 'ro');
grid on
xlabel('x/m（视图横轴向右方向）');
ylabel('y/m（视图纵轴向上）');
title('以与正北方向相应夹角线为纵轴的坐标系');

figure(6)
plot3(points_trans(:, 1), points_trans(:, 2), points_trans(:, 3), 'r*');
grid on
xlabel('x/m（视图横轴向右方向）');
ylabel('y/m（视图纵轴向上）');
zlabel('相对中心点的高程/m');
title('以与正北方向相应夹角线为纵轴的坐标系');
save positionResult.txt points_trans -ascii;

points_trans_abs = points_trans;
points_trans_abs(:,3) = point(:,3);
figure(7)
plot3(points_trans_abs(:, 1), points_trans_abs(:, 2), points_trans_abs(:, 3), 'r*');
grid on
xlabel('x/m（视图横轴向右方向）');
ylabel('y/m（视图纵轴向上）');
zlabel('高程/m');
title('以与正北方向相应夹角线为纵轴的坐标系');