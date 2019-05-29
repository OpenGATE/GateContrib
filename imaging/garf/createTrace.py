import torch
import garf
from torch.autograd import Variable
import json

nn, model = garf.load_nn("/home/tbaudier/david/gateTorch/gateContribExample/pth/arf.pth")

data_filename="/home/tbaudier/david/gateTorch/gateContribExample/output_arf_dataset/test.root"
data, x, y, theta, phi, E = garf.load_test_dataset(data_filename)

model_data = nn['model_data']
ax = data[:, 2:5]
tx = ax[0:400]

x_mean = model_data['x_mean']
x_std = model_data['x_std']
tx = (tx - x_mean) / x_std
dtypef = torch.cuda.FloatTensor
model.cuda()
tx = tx.astype('float32')
vx = Variable(torch.from_numpy(tx)).type(dtypef)

traced_script_module = torch.jit.trace(model, vx)
traced_script_module.save("model.pt")

#Save dict nn into json
model_data["x_mean"] = model_data["x_mean"].tolist()
model_data["x_std"] = model_data["x_std"].tolist()
model_data["loss_values"] = model_data["loss_values"].tolist()
outfile = open('nnDict.json', 'w')
json.dump(model_data, outfile)
print("done")
