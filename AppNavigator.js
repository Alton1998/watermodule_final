import {createStackNavigator} from 'react-navigation-stack'
import SignIn from './SignIn'
import  Chart from './Chart'
const AppNavigator = createStackNavigator(  
    {  
        SignIn: {screen:SignIn,
            navigationOptions:{  
                header:null,  
              }  
        }, 
        Chart:{
            screen:Chart,
            navigationOptions:{
                title:'Sump Water Level',
                headerLeft: null,
            }
        },
    },
    {  
        initialRouteName: "SignIn"  
    }  
  );
  export default AppNavigator;