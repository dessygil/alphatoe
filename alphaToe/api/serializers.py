from rest_framework import serializers
from .models import Scoreboard

class ScoreboardSerializer(serializers.ModelSerializer):
    class Meta:
        model = Scoreboard
        fields = ('id', 'user','computer_score','user_score')
        
