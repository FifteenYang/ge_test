function [ point_res ] = get_pos( point, point_cen )
%get_pos ��ȡ��������ϵ��ɫ����
%   ����ԭ���Լ���ת���ĵ㣨����γ�ȸ߶ȣ�
%   �����������ϵ�µĵ������
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

