import React from "react";
import Header from "../components/Header";
import AddAgent from "../components/AddAgent";
import AgentList from "../components/AgentList";

const Home = () => {
    return (
        <div>
            <Header />
            <AddAgent />
            <AgentList />
        </div>
    )
}

export default Home;