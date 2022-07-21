addpath('tools');

%% Read FE mesh of the soft gripper
fname1 = fullfile('database','mesh','gcrd.bin');
fname2 = fullfile('database','mesh','bfaces.bin');
gcrd = binread(fname1);		% FE nodal coordinates
bfaces = binread(fname2);	% FE mesh of boundary surface
nnode = size(gcrd,1);		% total number of FE nodes
sdof = 3*nnode; 			% 

% available validating parameters
fname1 = fullfile('database','para','paraval.bin');
fname2 = fullfile('database','para','dispval.bin');
fname3 = fullfile('database','para','misesval.bin');
paraval = binread(fname1);
dispval = binread(fname2);
misesval = binread(fname3);

%% new parameter and new FE solutions
paras = csvread('parameter.csv');
fname1 = fullfile('result','drom.bin');
fname2 = fullfile('result','mrom.bin');
disp_new = binread(fname1);
mises_new = binread(fname2);

%% Visualization
[valID] = knnsearch(paraval,paras,'K',1);
if norm(paraval(valID,:)-paras) > 1e-3
	% Abaqus solution for new parameter is not available 
	post_process_newsol;
else 
	% Abaqus solution for new parameter is available
	post_process_compare;
end

colormap(jet(12));

rmpath('tools');