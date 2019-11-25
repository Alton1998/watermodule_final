from django.shortcuts import render

# Create your views here.
from django.contrib.auth import get_user_model
from rest_framework.generics import CreateAPIView
from rest_framework.permissions import AllowAny
from rest_framework.response import Response
from rest_framework.authtoken.models import Token
from rest_framework import status
from rest_framework.views import APIView
from .serializers import CreateUserSerializer,TankReadingSerializer,TanksSerializer
from .models import Tank,Tank_Reading
class CreateUserAPIView(CreateAPIView):
    serializer_class = CreateUserSerializer
    permission_classes = [AllowAny]

    def create(self, request, *args, **kwargs):
        serializer = self.get_serializer(data=request.data)
        serializer.is_valid(raise_exception=True)
        self.perform_create(serializer)
        headers = self.get_success_headers(serializer.data)
        # We create a token than will be ued for future auth
        token = Token.objects.create(user=serializer.instance)
        token_data = {"token": token.key,}
        return Response(
            {**serializer.data, **token_data},
            status=status.HTTP_201_CREATED,
            headers=headers
        )


class LogoutUserAPIView(APIView):
    queryset = get_user_model().objects.all()

    def get(self, request, format=None):
        # simply delete the token to force a login
        request.user.auth_token.delete()
        return Response(status=status.HTTP_200_OK)

class TanksAPI(APIView):
    def get(self,request):
        data=Tank.objects.all()
        serializer=TanksSerializer(data,many=True)
        return Response(serializer.data)
    def post(self,request):
        serializer=TanksSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class TanksReadingAPI(APIView):
    def get(self,request):
        data=Tank_Reading.objects.all()
        serializer=TankReadingSerializer(data,many=True)
        return Response(serializer.data)
    def post(self,request):
        serializer=TankReadingSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class TanksReadingTankAPI(APIView):
    def get(self,request,Tank1):
        print(Tank1)
        data=Tank_Reading.objects.filter(Tank_Name=Tank1).order_by('id').reverse()[0]
        print(data)
        list=[]
        list.append(data)
        serializer = TankReadingSerializer(list, many=True)
        return Response(serializer.data)


