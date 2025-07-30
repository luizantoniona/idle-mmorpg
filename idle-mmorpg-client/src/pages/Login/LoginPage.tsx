import "./LoginPage.css";
import logo from '../../assets/logo.png';
import { LoginForm, ServerForm } from "./components/";

export function LoginPage() {
    return (
        <div className="login-grid">
            <div className="login-top">
                <ServerForm />
            </div>
            <div className="login-bottom">
                <LoginForm />
                <img src={logo} alt="Logo" />
            </div>
        </div>
    );
}