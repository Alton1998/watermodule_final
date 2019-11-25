import React, { Component, } from 'react';
import { Text, View,StyleSheet,TextInput,TouchableOpacity} from 'react-native';
import Splash from './Splash';
import axios from 'axios'

export default class Input extends Component
{
    constructor(props)
    {
        super(props)
        this.state={
          response:"",
          error:"",
        }
        this.handleLogin=this.handleLogin.bind(this)
    }
    handleLogin()
  {
    const {navigate}=this.props.navigation
    axios.post('http://192.168.43.158/watermodule/auth/login/', {
      username: this.state.Username,
      password: this.state.Password,
    })
    .then((response) => {
      console.log(response);
      this.setState(
        {
          response:response,
          error:"",
        }
      );
      console.log(this.state.response)
      navigate('Chart',{token:this.state.response.data.token})
    })
    .catch((error)=> {
      console.log(error);
      this.setState(
        {
          error:""+error,
        }
      )
      
    });
  }
    render()
    {
        return(
        <View style={styles.input}>
          <Splash style={styles.resize} textstyle={{fontSize:40}}/>
          <TextInput placeholder="Enter Username" style={styles.inputUsername} onChangeText={(Username) => this.setState({Username})} ></TextInput>
          <TextInput secureTextEntry={true} placeholder="Enter Password" style={styles.inputUsername} onChangeText={(Password) => this.setState({Password})}></TextInput>
          <View>
          <TouchableOpacity style={styles.buttonLogin} onPress={this.handleLogin} >
              <Text style={styles.buttonText}>Login</Text>
          </TouchableOpacity>
          </View>
          <Text style={{color:'red',position:'absolute',alignSelf:'center',top:230}}>
            {this.state.error}
          </Text>
      </View>
        )
    }
}
const styles = StyleSheet.create({
    input:
  {
      width:300,
  },
  label:
  {
      fontSize:20,
      alignSelf:"flex-start",
  },
  inputUsername:
  {
    alignSelf:"flex-start",   
    height:50,
    width:300,
    borderBottomColor:'#0D47A1',
    borderBottomWidth:1,
    fontSize:20,
    marginBottom: 30,
  },
  resize:
  {
    width:150,
    height:150,
    alignSelf:"center",
    position:'absolute',
    bottom:200,
  },
  buttonLogin:
  {
    backgroundColor:'#1565C0',
    width:300,
    height:50,
    alignItems: 'center',
    justifyContent: 'center',
    position:'absolute',
    borderRadius: 5,
  },
  buttonText:
  {
    color:'white',
    alignSelf:'center',
    fontSize:20,
  }
  });