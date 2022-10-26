from django.urls import path
from .views import ScoreboardView

urlpatterns = [
    path("", ScoreboardView.as_view())
]
