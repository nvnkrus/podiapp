% ============================================================
%    PODI-RBF PROGRAM FOR SNAP-CONNECTOR PROBLEM

% Target: approximate the displacement and von-Mises
% stress fields of the male and female connectors during the connection
% process. In the file `parameter.csv`, users can vary
% 	- the y-displacement `u_y` in [-3.2,0] mm
% The approximated solutions by PODI-RBF method are obtained
% in online stage and stored in `result` folder.
%             -----------------         
% For evaluation, Abaqus solutions of 30 cases are provided.
% 	Case	d	Case	d	Case	d
% 	1	-3.12	11	-2.08	21	-1.04
% 	2	-3.04	12	-2		22	-0.88
% 	3	-2.96	13	-1.84	23	-0.8
% 	4	-2.8	14	-1.76	24	-0.72
% 	5	-2.72	15	-1.68	25	-0.56
% 	6	-2.64	16	-1.52	26	-0.48
% 	7	-2.48	17	-1.44	27	-0.4
% 	8	-2.4	18	-1.36	28	-0.24
% 	9	-2.32	19	-1.2	29	-0.16
% 	10	-2.16	20	-1.12	30	-0.08

%% Description 
% This file is prepared for fast validtion of the software by running all 
% 30 testing cases using a single script.

%% 30 validating cases
paraval = ...
	[-3.12
	-3.04
	-2.96
	-2.8
	-2.72
	-2.64
	-2.48
	-2.4
	-2.32
	-2.16
	-2.08
	-2	
	-1.84
	-1.76
	-1.68
	-1.52
	-1.44
	-1.36
	-1.2
	-1.12
	-1.04
	-0.88
	-0.8
	-0.72
	-0.56
	-0.48
	-0.4
	-0.24
	-0.16
	-0.08];
nparaval = size(paraval,1);

%% Test the software only
% 	valIDs = 1:nparaval; 	% use this if you want to validate all 30 cases
% 	% valIDs = 1; 			% modify this if you want to test a subset of cases
% 
% 	%% Validating in a loop
% 	for id = 1:length(valIDs)
% 		valID = valIDs(id);
% 		paras = paraval(valID,:);
% 		csvwrite('parameter.csv', paras);
% 		system('./run_main.sh');
% 	end

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
	
	saveas(gcf,'test.fig','fig');