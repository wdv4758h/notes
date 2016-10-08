from django.db import models

# Create your models here.
class Test(models.Model):
    number = models.IntegerField(default=42)
