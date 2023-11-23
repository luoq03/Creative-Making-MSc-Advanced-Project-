# 情感识别算法设计和实现

## 选定数据集

![屏幕截图 2023-11-23 024006](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/bce88adc-40b6-46f4-a3e9-65a4890f0329)

![屏幕截图 2023-11-23 024108](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/0c713d6f-c599-473b-be9c-7a71de19eb06)

![屏幕截图 2023-11-23 024149](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/96533590-fccd-4fa9-bce4-bbb12840cb2c)

![屏幕截图 2023-11-23 024215](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/dd3f2e89-c3df-4a8f-96fb-63c5cffd00a6)

![屏幕截图 2023-11-23 024237](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/5ffc2456-046f-4ff8-8a44-6874447adeb9)

![屏幕截图 2023-11-23 024255](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/37fae7ae-4522-478b-8eea-80c5fbabc77f)

![屏幕截图 2023-11-23 024324](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/aaca29d0-dcc4-45d9-8703-dd81803819fa)

![屏幕截图 2023-11-23 024341](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/92058745-7074-4623-8119-4c29d032fa83)

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

## 分配损失函数和优化器

```ruby
loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(base_model_resnet18.parameters(), lr=1e-3)
```

## 训练和评估

```ruby
%%time
epochs = 60
train_loss_list = []
train_acc_list = []
test_loss_list = []
test_acc_list = []
for t in range(epochs):
    print(f"Epoch {t+1}\n-------------------------------")
    train(train_dl, base_model_resnet18, loss_fn, optimizer)
    train_loss, train_correct = test(train_dl, base_model_resnet18, loss_fn)
    test_loss, test_correct = test(test_dl, base_model_resnet18, loss_fn)
    train_loss_list.append(train_loss)
    train_acc_list.append(train_correct)
    test_loss_list.append(test_loss)
    test_acc_list.append(test_correct)
print("Done!")
```

![屏幕截图 2023-11-23 115214](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/5ccf5093-f445-490b-88f6-82f65b3ecbf4)

![屏幕截图 2023-11-23 115257](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/d6720123-b91d-409e-9b2b-eb8f36a78bee)

![屏幕截图 2023-11-23 115325](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/fda11258-5e61-49f2-b4d7-a98c09ecc635)

![屏幕截图 2023-11-23 115344](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/47e8a179-071a-47bd-893f-b15b945102a3)

![屏幕截图 2023-11-23 115406](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/2b2b1e78-d40d-4f50-9dc2-a6218dbd0444)

![屏幕截图 2023-11-23 115429](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/ddbf620b-f89e-48fd-9ad4-3eeee952ce33)

![屏幕截图 2023-11-23 115453](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/cb415886-4792-4024-adb3-026f598fc1a5)






















































































































































































































