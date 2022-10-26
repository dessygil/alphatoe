from django.shortcuts import render
from rest_framework import generics
from .serializers import ScoreboardSerializer
from .models import Scoreboard
from rest_framework.views import APIView
from rest_framework.response import Response

# Create your views here.

class ScoreboardView(generics.CreateAPIView):
    queryset = Scoreboard.objects.all()
    serializer_class = ScoreboardSerializer
