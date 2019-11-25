import React, { Component, } from 'react';
import {View,StyleSheet} from 'react-native';
import Input from './Input.js'


export default class SignIn extends Component {
    
    
    render() {
      return (
        <View style={styles.content}>
          <Input navigation={this.props.navigation}/>
        </View>
      );
    }
  }
  const styles = StyleSheet.create({
    splash:{
      flex: 1, 
      justifyContent: "center", 
      alignItems: "center",
      backgroundColor: '#448AFF',
    },
    content:{
      flex:1,
      flexDirection:"column",
      justifyContent:"space-around",
      alignItems:"center",
    },
  });