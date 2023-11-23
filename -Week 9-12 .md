# 情感识别算法设计和实现-训练情绪识别模型
## 选定数据集

![屏幕截图 2023-11-23 144303](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/3c413051-4e99-479b-83f0-ee615627af83)


### 数据集内图像样本-以angry为例
![屏幕截图 2023-11-23 024108](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/627ee4f0-7f48-4bbd-8760-28b0b12f7a91)

## 从kaggle下载数据集

```ruby
!cp /content/drive/MyDrive/kaggle.json /content/
```

```ruby

!mkdir -p ~/.kaggle

!cp kaggle.json ~/.kaggle/

!chmod 600 ~/.kaggle/kaggle.json

```

```ruby

!kaggle datasets download -d jonathanoheix/face-expression-recognition-dataset

```

```ruby

!unzip /content/face-expression-recognition-dataset.zip

```
## 导入python包

```ruby
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
from torchvision import models
import matplotlib.pyplot as plt
import numpy as np
import os
from PIL import Image
import pandas as pd
import seaborn as sns
from sklearn.metrics import confusion_matrix, classification_report
import time
import copy
```

## 超参数设置

```ruby
batch_size = 16
epochs = 10
learning_rate = 0.01
img_width= 224
img_height= 224
```

## 数据预处理pipline

### 准备dataset

```ruby
train_dir = '/content/images/train'
test_dir = '/content/images/validation'
```
![屏幕截图 2023-11-23 112101](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/f001b2b7-a610-4e44-a472-d1ae96dbcf39)

### 准备dataloader
```ruby
train_dl = torch.utils.data.DataLoader(train_ds, batch_size=batch_size, shuffle=True)
test_dl = torch.utils.data.DataLoader(test_ds, batch_size=batch_size, shuffle=True)

# train_dl = torch.utils.data.DataLoader(train_ds_mini, batch_size=batch_size, shuffle=True)
# test_dl = torch.utils.data.DataLoader(test_ds_mini, batch_size=batch_size, shuffle=True)
```
### 确定数据输入shape

![屏幕截图 2023-11-23 112453](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/70c4944c-4792-413f-ba1a-686fa1b9757b)

## 确认GPU CPU使用情况

![屏幕截图 2023-11-23 112845](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/d315a121-960c-4efa-a953-74b58c4c85d2)

## 训练和评估循环

```ruby
def train(dataloader, model, loss_fn, optimizer):
    size = len(dataloader.dataset)
    model.train()
    for batch, (img_rgb, y) in enumerate(dataloader):
        # X, y = X.to(device), y.to(device)
        img_rgb = img_rgb.to(device)
        y = y.to(device)
        # Compute prediction error
        pred = model(img_rgb)
        loss = loss_fn(pred, y)
        # Backpropagation
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        if batch % 50 == 0:
            loss, current = loss.item(), batch * len(img_rgb)
            print(f"loss: {loss:>7f}  [{current:>5d}/{size:>5d}]")


def test(dataloader, model, loss_fn):
    size = len(dataloader.dataset)
    num_batches = len(dataloader)
    model.eval()
    test_loss, correct = 0, 0
    with torch.no_grad():
        for (img_rgb, y) in dataloader:
            img_rgb = img_rgb.to(device)
            y = y.to(device)
            pred = model(img_rgb)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()
    test_loss /= num_batches
    correct /= size
    print(f"Test Error: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")
    return test_loss, correct
```

## 模型 resnet18

### 确定数据输入shape

![屏幕截图 2023-11-23 114614](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/b62aaea8-c49a-464e-b5fb-6accc6bc2d72)

![屏幕截图 2023-11-23 114704](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/af0910e4-caf0-404f-9006-d248b1f188ea)

### 分配损失函数和优化器

```ruby
loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(base_model_resnet18.parameters(), lr=1e-3)
```

### 训练和评估

![屏幕截图 2023-11-23 120124](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/7773236e-27f2-4e4d-a7f0-94d4673f5b80)

![屏幕截图 2023-11-23 115214](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/5ccf5093-f445-490b-88f6-82f65b3ecbf4)

![屏幕截图 2023-11-23 115257](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/d6720123-b91d-409e-9b2b-eb8f36a78bee)

![屏幕截图 2023-11-23 115325](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/fda11258-5e61-49f2-b4d7-a98c09ecc635)

![屏幕截图 2023-11-23 115344](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/47e8a179-071a-47bd-893f-b15b945102a3)

![屏幕截图 2023-11-23 115406](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/2b2b1e78-d40d-4f50-9dc2-a6218dbd0444)

![屏幕截图 2023-11-23 115429](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/ddbf620b-f89e-48fd-9ad4-3eeee952ce33)

![屏幕截图 2023-11-23 115453](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/cb415886-4792-4024-adb3-026f598fc1a5)

### 可视化训练过程

```ruby
# train_loss_array,train_acc_array,val_loss_array,val_acc_array
acc = train_acc_list
val_acc = test_acc_list
loss = train_loss_list
val_loss = test_loss_list
epochs_range = range(epochs)
plt.figure(figsize=(8, 8))
plt.subplot(1, 2, 1)
plt.plot(epochs_range, acc, label='Training Accuracy')
plt.plot(epochs_range, val_acc, label='Validation Accuracy')
plt.legend(loc='lower right')
plt.title('Training and Validation Accuracy')
plt.subplot(1, 2, 2)
plt.plot(epochs_range, loss, label='Training Loss')
plt.plot(epochs_range, val_loss, label='Validation Loss')
plt.legend(loc='upper right')
plt.title('Training and Validation Loss')
plt.show()
```
![屏幕截图 2023-11-23 115926](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/ab3ddb06-8d4b-4544-ab3d-a7aafecec5bc)

### 模型验证集预测

```ruby

predict_list = []
label_list = []
predict_pro_list = []
m_softmax = nn.Softmax(dim=1)
for (img_rgb, y) in test_dl:
    img_rgb = img_rgb.to(device)
    y = y.to(device)

    predict_score = base_model_resnet18(img_rgb)
    predict_pro = m_softmax(predict_score)

    predict_label = np.argmax(predict_score.detach().cpu().numpy(),axis=1)

    predict_pro_list.append(predict_pro.detach().cpu().numpy())
    predict_list.append(predict_label)
    label_list.append(y.detach().cpu().numpy())

predict_pro_array = np.vstack(predict_pro_list)[:,1]
predict_array = np.hstack(predict_list)
label_array = np.hstack(label_list)
predict_pro_array[:5],predict_array[:5],label_array[:5]

```

![屏幕截图 2023-11-23 120627](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/04c948de-0ec1-4533-bc19-9b8983bd682c)

#### 分类报告

![屏幕截图 2023-11-23 120805](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/830818f5-02e2-4861-aa12-82883c42eed6)

#### 混淆矩阵

![屏幕截图 2023-11-23 120851](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/d2dc6521-1b41-41bb-a811-151a17134b8a)

![屏幕截图 2023-11-23 120912](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/14f1422e-432e-4cb5-9d8a-103d0c73ede9)

![屏幕截图 2023-11-23 120925](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/bad4f2e2-ec4f-4e72-8161-ad5cf66c6f2d)

## 在训练情绪模型的过程中，我也尝试了另外两组模型----cnn模型和模型 swin_transformer

### cnn模型 

```ruby
class CNN(nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = nn.Conv2d(3, 6, 3)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 3)
        self.conv3 = nn.Conv2d(16, 32, 3)
        self.conv4 = nn.Conv2d(32, 32, 3)
        self.fc1 = nn.Linear(4608, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, num_classes)
    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = self.pool(F.relu(self.conv3(x)))
        x = self.pool(F.relu(self.conv4(x)))
        x = torch.flatten(x, 1) # flatten all dimensions except batch
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

cnn_model = CNN().to(device)

cnn_model(b_img.to(device)).shape

```

```ruby
%%time
epochs = 60
train_loss_list = []
train_acc_list = []
test_loss_list = []
test_acc_list = []
for t in range(epochs):
    print(f"Epoch {t+1}\n-------------------------------")
    train(train_dl, cnn_model, loss_fn, optimizer)

    train_loss, train_correct = test(train_dl, cnn_model, loss_fn)
    test_loss, test_correct = test(test_dl, cnn_model, loss_fn)
    train_loss_list.append(train_loss)
    train_acc_list.append(train_correct)
    test_loss_list.append(test_loss)
    test_acc_list.append(test_correct)
print("Done!")

```

![屏幕截图 2023-11-23 130911](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/f3db3131-4600-4752-8719-a2bf0dd4744d)

![屏幕截图 2023-11-23 131055](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/488f2ae9-bf1e-4ae6-8abb-3911068644f6)

![屏幕截图 2023-11-23 131142](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/dc18922f-7742-421c-ac40-e9a637d1aa98)

![屏幕截图 2023-11-23 131153](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/47a315df-4d89-43f9-8dac-900519eef663)

![屏幕截图 2023-11-23 131202](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/1785ed74-26c3-4932-abfa-0d1ccd4de955)


### 模型 swin_transformer

#### 构建基础模型

![屏幕截图 2023-11-23 133916](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/3298c118-4826-40fe-9635-df4c5f580b71)

#### 分配损失函数和优化器

```ruby
loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(base_model_swin.parameters(), lr=1e-3)
```
#### 训练和评估

![屏幕截图 2023-11-23 134216](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/2396acaf-72df-4f0a-aad7-f75d40decdb6)

![屏幕截图 2023-11-23 134252](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/f07d8f17-047c-42b5-b2c2-d0b36ad5b72c)

#### 可视化训练过程

![屏幕截图 2023-11-23 134348](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/dcfeb7e4-dc9f-46e8-bb2e-21019b277ff3)

![屏幕截图 2023-11-23 134422](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/f70a5f3c-2e7c-4333-96a5-45b3299dce01)

#### 模型验证集预测

![屏幕截图 2023-11-23 134816](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/cb55bb67-abe5-48d9-9e64-9a082e990d84)

![屏幕截图 2023-11-23 134902](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/1e6c1c9e-8316-4264-a078-1aaf3bb9dc3e)

![屏幕截图 2023-11-23 134932](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/14ada370-7e4d-4369-8f08-5ecd35069522)

![屏幕截图 2023-11-23 134947](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/596dda98-0918-4231-945c-df6e708d4167)

![屏幕截图 2023-11-23 134959](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/efc681db-9a18-46e0-a596-fd36b7bf0446)

# 情感识别算法设计和实现-与openCV结合

## 导入python包

```ruby
import torch
import cv2
from torchvision import models, transforms
import serial
import serial.tools.list_ports
import time
import math

```

```ruby
import torch
import torchvision.models as models
import torchvision.transforms as transforms
from PIL import Image
from torch import nn
import numpy as np

```

## 导入之前训练好的模型，导入标签，设置串口与Arduino通信

```ruby
ser = serial.Serial('/dev/cu.usbserial-144140', 115200,timeout=1)
num=0 
label_name_list = ['angry', 'disgust', 'fear', 'happy', 'neutral', 'sad', 'surprise']
save_path = "resnet18v1.pth"
num_classes = len(label_name_list)
img_width = 224

# 定义一个预测函数
# 加载预训练的 ResNet-18 模型
model_reload = models.resnet18(pretrained=True)
num_ftrs = model_reload.fc.in_features
model_reload.fc = nn.Linear(num_ftrs, num_classes)
# model_reload.to('cpu')
model_reload.load_state_dict(torch.load(save_path,map_location=torch.device('cpu')))
```

![屏幕截图 2023-11-23 122928](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/85b5ba5d-6bf4-4809-8e7e-dca41b43f0c2)

```ruby
ser = serial.Serial('/dev/cu.usbserial-144140', 115200,timeout=1)
num=0 
label_name_list = ['angry', 'disgust', 'fear', 'happy', 'neutral', 'sad', 'surprise']
save_path = "resnet18v1.pth"
num_classes = len(label_name_list)
img_width = 224

# 定义一个预测函数
# 加载预训练的 ResNet-18 模型
model_reload = models.resnet18(pretrained=True)
num_ftrs = model_reload.fc.in_features
model_reload.fc = nn.Linear(num_ftrs, num_classes)
# model_reload.to('cpu')
model_reload.load_state_dict(torch.load(save_path,map_location=torch.device('cpu')))
```

## 情绪识别

```ruby
# 图像预处理
# ori = image.copy()
pred_transform = transforms.Compose([
                    transforms.ToPILImage(),
                    transforms.Resize((img_width,img_width)),
                    transforms.ToTensor(),
                    transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
                    ])



# 定义一个预测函数
def predict(image):

    model_reload.eval()
    # 进行预测
    with torch.no_grad():
        outputs = model_reload(image)
        _, preds = torch.max(outputs, 1)
        # 计算预测概率
        pred_score_list = nn.functional.softmax(outputs[0], dim=0).cpu().numpy()
        # 获取最大值
        pred_score = np.max(pred_score_list)

    # 预测最可能的类别
    predicted_idx = str(preds[0].item())
    label_name = label_name_list[preds[0].item()]
    return label_name,str(pred_score)  # 返回预测结果和处理后的图像
```

## 连接openCV并显示情绪标签

```ruby

# 使用OpenCV捕获摄像头视频
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        print("Error: failed to capture image")
        break

    # 将BGR图像转换为RGB，然后应用预处理
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    image = pred_transform(rgb_frame).unsqueeze(0)  # 添加批处理维度
    #img_tensor = transform(rgb_frame)
    #img_tensor = img_tensor.unsqueeze(0)  # 添加批次维度
    label_name,pred_score =  predict(image)



    # 在帧上显示预测结果
    cv2.putText(frame, label_name, (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # print ("label_name >",label_name)
    ser.write(label_name.encode('utf-8'))
    #comdata=label_name+'0'
    #ser.write(comdata.encode('utf-8'))
    #num=num+1
    #if num==10:
     #   comdata=label_name+'0'
     #   num=0
     #   ser.write(comdata.encode('utf-8'))
        # ser.flushOutput()  # 清空发送缓存
    time.sleep(0.1)
    # 显示帧
    cv2.imshow('frame', frame)

    # if cv2.waitKey(1) & 0xFF == ord('q'):
    #     break

    if cv2.waitKey(1)  == 27:
        break
# 释放摄像头资源
cap.release()
cv2.destroyAllWindows()

```

## 结果展示
![屏幕截图 2023-11-23 135740](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/21d0c018-e6a9-4f43-b385-be34888c3f24)

![屏幕截图 2023-11-23 135656](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/6c360f58-19e3-422c-941c-09ec7ad7438e)

![屏幕截图 2023-11-23 135610](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/8bb8f8bc-4480-4f92-897c-6ebfa2f51eeb)

![屏幕截图 2023-11-23 135542](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/0110f468-4c65-4c43-adb4-de7127b6588a)

















