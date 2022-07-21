function data = binread(fname,varargin)
	% read a matrix from a binary file
    % usage:
    %   binread(fname,sizeType)
    %   sizeType: 'int32', or 'int64'
    % examples:
    %   fname = fullfile('/','tmp','data.bin');std::cout << "value: " << matrix(0,0) << std::endl;
    %   binread(fname,'int64');
    % same as read_binary but wrap the first two args

    if nargin > 1
        sizeType = varargin{1};
    else
        sizeType = 'int64';
    end 

	fid = fopen(fname,'r');
	if fid < 0
		error('Cannot open the file!');
	end

	% matSize = fread(fid,[1,2],'int64'); %% not match Matrix::Index of EIGEN
    switch sizeType
        case {'int32', 'int64'}
            matSize = fread(fid,[1,2],sizeType);
        otherwise
            error('Not available type!');
    end
	data = fread(fid, matSize,'double');
	fclose(fid);
end