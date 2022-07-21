% ============================================================
%    PODI-RBF PROGRAM FOR WIRE-WINDING PROBLEM

% Target: approximate the displacement and von-Mises
% stress fields of the deformable wire during the winding
% process. The wire is winded around a rigid cylinder of 
% radius 15 mm by simultaneously rotate and translate the cylinder.
% In the file `parameter.csv`, users can vary
% 	- the Young's modulus `E` in [5e4,25e4] MPa
% 	- the ratio of translation/rotation speed `R` in [1,3]
% 	- the pressure at one end of the wire `P` in [1,3] MPa.
% The approximated solutions by PODI-RBF method are obtained
% in online stage and stored in `result` folder.
%             -----------------         
% For evaluation, Abaqus solutions of 30 cases are provided.

%% Description 
% This file is prepared for fast validtion of the software by running all 
% 30 testing cases using a single script.

%% 30 validating cases
paraval = ...
	[75000	1.3	1.75
	75000	1.3	2.25
	75000	1.3	2.75
	75000	1.7	1.75
	75000	1.7	2.25
	75000	1.7	2.75
	75000	2.1	1.75
	75000	2.1	2.25
	75000	2.1	2.75
	75000	2.5	1.75
	75000	2.5	2.25
	75000	2.5	2.75
	75000	2.9	1.75
	75000	2.9	2.25
	75000	2.9	2.75
	225000	1.3	1.75
	225000	1.3	2.25
	225000	1.3	2.75
	225000	1.7	1.75
	225000	1.7	2.25
	225000	1.7	2.75
	225000	2.1	1.75
	225000	2.1	2.25
	225000	2.1	2.75
	225000	2.5	1.75
	225000	2.5	2.25
	225000	2.5	2.75
	225000	2.9	1.75
	225000	2.9	2.25
	225000	2.9	2.75];
nparaval = size(paraval,1);

%% Test the software only
	valIDs = 1:nparaval; 	% use this if you want to validate all 30 cases
	% valIDs = 1; 			% modify this if you want to test a subset of cases

	%% Validating in a loop
	for id = 1:length(valIDs)
		valID = valIDs(id);
		paras = paraval(valID,:);
		csvwrite('parameter.csv', paras);
		system('./run_main.sh');
	end

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