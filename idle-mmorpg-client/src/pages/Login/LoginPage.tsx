import "./LoginPage.css";
import logo from '../../assets/logo.png';
import { LoginForm, ServerForm } from "./components/";

export function LoginPage() {
    return (
        <div className="login-page">
            <ServerForm />
            <img src={logo} alt="Logo" />
            <LoginForm />
        </div>
    );
}