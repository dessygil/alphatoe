import React, { Component } from 'react';
import { BrowserRouter as Router, Switch, Route, Link, Redirect, Routes } from 'react-router-dom'


export default class HomePage extends Component {
    constructor(props) {
        super(props);
    }
    render(){
        return <Router>
            <Routes>
                <Route exact path="/" element={<HomePage />} />
            </Routes>
        </Router>;
    };
}
