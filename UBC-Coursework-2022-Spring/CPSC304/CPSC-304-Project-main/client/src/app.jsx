import React from "react";
import {BrowserRouter as Router, Routes, Route} from "react-router-dom";
import Home from "./routes/Home";
import AgentDetailPage from "./routes/AgentDetailPage";
import AgentUpdatePage from "./routes/AgentUpdatePage";
import {AgentsContextProvider} from "./context/AgentsContext";

const App = () => {
    return (
    <AgentsContextProvider>
        <div className="container">
            <Router>
                <Routes>
                    <Route exact path="/" element={<Home/>}/>
                    <Route exact path="/agents/:id" element={<AgentDetailPage/>}/>
                    <Route exact path="/agents/:id/update" element={<AgentUpdatePage/>}/>
                </Routes>
            </Router>
        </div>
    </AgentsContextProvider>)
}

export default App;