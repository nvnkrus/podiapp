fprintf('==============================================\n');
fprintf('Abaqus solution is not available for this case:\n')
fprintf('\n\tYoung modulus E = %d MPa\n\tspeed ratio R = %.2f\n\tpressure P = %.2f MPa\n', paras(1), paras(2), paras(3));

%% PODI-RBF solution
snap_new = zeros(nnode,4);
snap_new(:,1:3) = reshape(disp_new,3,nnode)';
snap_new(:,4) = mises_new;

figure;
dispmat = snap_new(:,1:3);
% podi displacement - Ux
subplot(1,4,1); 
dispmag = snap_new(:,1);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z'); ylim([-50,500]);
title('PODI-RBF solution - Ux');

% podi displacement - Uy
subplot(1,4,2); 
dispmag = snap_new(:,2);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z'); ylim([-50,500]);
title('PODI-RBF solution - Uy');

% podi displacement - Uz
subplot(1,4,3); 
dispmag = snap_new(:,3);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z'); ylim([-50,500]);
title('PODI-RBF solution - Uz');

% podi displacement - von-Mises
subplot(1,4,4); 

dispmag = snap_new(:,4);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z'); ylim([-50,500]);
title('PODI-RBF solution - von-Mises');


set(gcf,'Position',[1,1,1818,1003]);