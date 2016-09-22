function [ dis ] = get_distance( point_a, point_b )
%get_distance 根据两点的经纬度数据，获取两点之间的距离
%   输入两点的经纬度数据
%   输出两点之间的距离
R = 6371.004;
C = sin(point_a(2)*pi/180)*sin(point_b(2)*pi/180) + ...
    cos(point_a(2)*pi/180)*cos(point_b(2)*pi/180)*...
    cos((point_a(1) - point_b(1))*pi/180);
dis = R * acos(C);%*pi/180;

end

