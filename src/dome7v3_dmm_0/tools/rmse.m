function err = rmse(apprx, exact, dim)    
    [m,n] = size(apprx);
    % for vector
    if m==1 || n ==1
        errvec = apprx - exact;
        err = sqrt(sum(errvec.^2)/m/n);
        return;
    end
    
    % for matrix
    if nargin < 3
        dim = 1;
    end
    
    if dim == 1
        err = zeros(1,n);
        for i=1:n
            err(i) = rmse(apprx(:,i),exact(:,i));
        end
    elseif dim == 2
        err = zeros(m,1);
        for i=1:m
            err(i) = rmse(apprx(i,:),exact(i,:));
        end
    end
end