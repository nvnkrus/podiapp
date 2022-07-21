function err = rtne(apprx, exact, dim)
% relative two norm error in [0,1]
% function err = rtne(apprx, exact, dim)    
%   dim = 1: error computed column-wise 
%   dim = 2: error computed row-wise 
% Examples: 
% A = [1 2 3; 4 5 6; 7 8 9]; 
% B = [1 2 3; 4 5.1 6; 7.1 8 9];
% rtne(A,B,1)
% rtne(A,B,2)
    [m,n] = size(apprx);
    % for vector
    if m==1 || n ==1
        err = norm(apprx - exact)/norm(exact);
        return;
    end
    
    % for matrix
    if nargin < 3
        dim = 1;
    end
    
    if dim == 1
        err = zeros(1,n);
        for i=1:n
            err(i) = rtne(apprx(:,i),exact(:,i));
        end
    elseif dim == 2
        err = zeros(m,1);
        for i=1:m
            err(i) = rtne(apprx(i,:),exact(i,:));
        end
    end
end