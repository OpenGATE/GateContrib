import torch
import garf
from torch.autograd import Variable
import json
import numpy as np

nn, model = garf.load_nn("/home/tbaudier/david/gateTorch/gateContribExample/pth/arf.pth")

model_data = nn['model_data']

tx = np.random.rand(1,3) # generate 3 random values between 0 and 1
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
