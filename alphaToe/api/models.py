from django.db import models

# Create your models here.
class Scoreboard(models.Model):
    user = models.CharField(max_length=50, default=generate_unique_code,unique=True)
    computer_score = models.IntegerField(null=False, default=0)
    user_score = models.IntegerField(null=False, default=0)
