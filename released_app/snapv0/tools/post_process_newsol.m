fprintf('==============================================\n');
fprintf('Abaqus solution is not available for this case:\n')
fprintf('\td = %.4f\n',paras);

figure;
dispmat = reshape(disp_new,3,nnode)';
% podi displacement - Ux
subplot(1,4,1); 
dispmag = dispmat(:,1);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Ux');

% podi displacement - Uy
subplot(1,4,2); 
dispmag = dispmat(:,2);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Uy');

% podi displacement - Uz
subplot(1,4,3); 
dispmag = dispmat(:,3);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Uz');

% podi displacement - von-Mises
subplot(1,4,4); 

dispmag = mises_new;
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - von-Mises');

set(gcf,'Position',[1,1,1818,1003]);