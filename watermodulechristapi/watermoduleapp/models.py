from django.db import models

# Create your models here.
class Tank(models.Model):
    Tank_Name=models.CharField(max_length=25);
    def __str__(self):
        return self.Tank_Name

class Tank_Reading(models.Model):
    Date=models.DateField(auto_now_add=True)
    Time=models.TimeField(auto_now_add=True)
    Tank=models.ForeignKey(Tank,on_delete=models.CASCADE,related_name='Tank')
    Tank_Reading_Recieved=models.PositiveIntegerField();
    Tank_Name=models.CharField(max_length=25,default="")

    def save(self, *args, **kwargs):
        self.Tank_Name=self.Tank.Tank_Name
        super().save(*args, **kwargs)