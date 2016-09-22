function [ point_res ] = get_pos( point, point_cen )
%get_pos 获取地面坐标系下色坐标
%   输入原点以及待转换的点（经度纬度高度）
%   输出地面坐标系下的点的坐标
point_tmp = point;
point_tmp(1) = point_cen(1);
x = 1000 * get_distance(point_tmp, point);
if(point(1) < point_cen(1))
    x = -x;
end

point_tmp =point;
point_tmp(2) = point_cen(2);
y = 1000 * get_distance(point_tmp, point);
if(point(2) < point_cen(2))
    y = -y;
end

z = point(3) - point_cen(3);
% z = point(3);
point_res = [x, y, z];
    
end

