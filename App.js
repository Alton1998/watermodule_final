import React from 'react';
import {View,Text,StyleSheet} from 'react-native'
import Splash from './Splash'
import AppNavigator from './AppNavigator'
import {createAppContainer } from 'react-navigation';

const AppContainer = createAppContainer(AppNavigator);  
export default class App extends React.Component
{
    constructor(props)
    {
        super(props)
        this.state={
            isLoading:true,
        }
    }
    componentDidMount()
    {
      setTimeout(() => {
        this.setState({isLoading: false});
      },5000)
    }
    render()
    {
        if(this.state.isLoading)
        {
        return(
            <View style={styles.splash}>
                <Splash/>
            </View>
        )
        }
        return <AppContainer />;
    }
}
const styles = StyleSheet.create({
    splash:{
      flex: 1, 
      justifyContent: "center", 
      alignItems: "center",
      backgroundColor: '#448AFF',
    },
  });