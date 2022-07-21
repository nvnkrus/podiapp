% ============================================================
%    PODI-RBF PROGRAM FOR SOFT GRIPPER PROBLEM

% Target: approximate the displacement and von-Mises
% stress fields of the soft gripper during the gripping
% process. The gripped object is a rigid cylinder of 
% radius 15 mm. In the file `parameter.csv`, users can vary
% 	- the cylinder position `h` in [40,100] mm
% 	- the cylinder incline angle `theta_x` in [-30,30] degree
% 	- the gripping distance `d_x` in [0,15] mm.
% The approximated solutions by PODI-RBF method are obtained
% in online stage and stored in `result` folder.
%             -----------------         
% For evaluation, Abaqus solutions of 30 cases are provided.

%% Description 
% This file is prepared for fast validtion of the software by running all 
% 30 testing cases using a single script.

%% 30 validating cases
paraval = ...
	[55, 15, 2.5
	55, 15, 7.5
	55, 15, 10
	55, 15, 15
	95, 15, 2.5
	95, 15, 7.5
	95, 15, 10
	95, 15, 15
	65, 15, 5
	65, 15, 7.5
	65, 15, 10
	65, 15, 12.5
	62.5, 0, 5
	62.5, 0, 7.5
	62.5, 0, 12.5
	62.5, 15, 2.5
	62.5, 15, 5
	62.5, 15, 7.5
	62.5, 15, 10
	62.5, 15, 12.5
	62.5, 15, 15
	77.5, 0, 2.5
	77.5, 0, 10
	77.5, 0, 15
	77.5, 15, 2.5
	77.5, 15, 5
	77.5, 15, 7.5
	77.5, 15, 10
	77.5, 15, 12.5
	77.5, 15, 15];
nparaval = size(paraval,1);

%% Test the software only
	% valIDs = 1:nparaval; 	% use this if you want to validate all 30 cases
	% % valIDs = 1; 			% modify this if you want to test a subset of cases

	% %% Validating in a loop
	% for id = 1:length(valIDs)
	% 	valID = valIDs(id);
	% 	paras = paraval(valID,:);
	% 	csvwrite('parameter.csv', paras);
	% 	system('./run_main.sh');
	% end

%% Test the software only + visualization
% it is recommended to run one case at a time
	valIDs = 1; 				% modify to choose a test case

	%% Validating in a loop
	for id = 1:length(valIDs)
		valID = valIDs(id);
		paras = paraval(valID,:);
		csvwrite('parameter.csv', paras);
		system('./run_main.sh');

		post_process;
	end