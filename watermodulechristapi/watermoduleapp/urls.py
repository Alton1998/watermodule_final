from django.conf.urls import url
from rest_framework.authtoken.views import obtain_auth_token
from .views import CreateUserAPIView, LogoutUserAPIView,TanksReadingAPI,TanksAPI,TanksReadingTankAPI

urlpatterns = [
    url(r'^auth/login/$',
        obtain_auth_token,
        name='auth_user_login'),
    url(r'^auth/register/$',
        CreateUserAPIView.as_view(),
        name='auth_user_create'),
    url(r'^auth/logout/$',
        LogoutUserAPIView.as_view(),
        name='auth_user_logout'),
    url(r'^Tanks/$',TanksAPI.as_view()),
    url(r'^TanksReading/$',TanksReadingAPI.as_view()),
    url(r'^TanksReading/(?P<Tank1>[\w\-]+)/$',TanksReadingTankAPI.as_view()),
]